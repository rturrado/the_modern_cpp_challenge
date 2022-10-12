#include "chapter_11_cryptography/problem_094_file_signing.h"
#include "env.h"

#include <cryptopp/files.h>  // FileSink, FileSource
#include <cryptopp/hex.h>  // HexDecoder, HexEncoder
#include <cryptopp/osrng.h>  // AutoSeededRandomPool
#include <cryptopp/rsa.h>  // RSAES_OAEP_SHA_{Decryptor, Encryptor}, RSASSA_PKCS1v15_SHA_{Signer, Verifier}
#include <filesystem>
#include <fmt/ostream.h>
#include <ostream>
#include <rtc/filesystem.h>

namespace fs = std::filesystem;


namespace tmcppc::crypto {
    void generate_keys(const fs::path& rsa_private_key_file_path, const fs::path& rsa_public_key_file_path) {
        using namespace CryptoPP;

        AutoSeededRandomPool rng{};

        RSAES_OAEP_SHA_Decryptor private_key{ rng, 3072 };
        HexEncoder private_file{ new FileSink{ rsa_private_key_file_path.c_str() } };
        private_key.AccessMaterial().Save(private_file);
        private_file.MessageEnd();

        RSAES_OAEP_SHA_Encryptor public_key{ private_key };
        HexEncoder public_file{ new FileSink{ rsa_public_key_file_path.c_str() } };
        public_key.AccessMaterial().Save(public_file);
        public_file.MessageEnd();
    }


    void sign_file(const fs::path& input_file_path, const fs::path& rsa_private_key_file_path, const fs::path& signature_file_path) {
        using namespace CryptoPP;

        if (not fs::exists(input_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ input_file_path.generic_string() };
        }
        if (not fs::exists(rsa_private_key_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ rsa_private_key_file_path.generic_string() };
        }

        AutoSeededRandomPool rng{};

        FileSource private_file{ rsa_private_key_file_path.c_str(), true, new HexDecoder{} };
        RSASSA_PKCS1v15_SHA_Signer signer{ private_file };

        FileSource input_file_source{
            input_file_path.c_str(),
            true,
            new SignerFilter{
                rng,
                signer,
                new HexEncoder{
                    new FileSink{
                        signature_file_path.c_str()
                    }
                }
            }
        };
    }


    bool verify_file(const fs::path& input_file_path, const fs::path& rsa_public_key_file_path, const fs::path& signature_file_path) {
        using namespace CryptoPP;

        if (not fs::exists(input_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ input_file_path.generic_string() };
        }
        if (not fs::exists(rsa_public_key_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ rsa_public_key_file_path.generic_string() };
        }
        if (not fs::exists(signature_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ signature_file_path.generic_string() };
        }

        FileSource public_file{ rsa_public_key_file_path.c_str(), true, new HexDecoder{} };
        RSASSA_PKCS1v15_SHA_Verifier verifier{ public_file };

        FileSource signature_file{ signature_file_path.c_str(), true, new HexDecoder{} };
        if (signature_file.MaxRetrievable() != verifier.SignatureLength()) {
            return false;
        }
        SecByteBlock signature{ verifier.SignatureLength() };
        signature_file.Get(signature, signature.size());

        SignatureVerificationFilter* verifierFilter{ new SignatureVerificationFilter(verifier) };
        verifierFilter->Put(signature, verifier.SignatureLength());

        FileSource input_file_source{
            input_file_path.c_str(),
            true,
            verifierFilter
        };

        return verifierFilter->GetLastResult();
    }
}  // namespace tmcppc::problem_94


// File signing
//
// Write a program that is able to sign files and verify that a signed file has not been tampered with, using RSA cryptography.
// When signing a file, the signature should be written to a separate file and used later for the verification process.
// The program should provide at least two functions:
//   - one that signs a file (taking as arguments the path to the file, the path to the RSA private key, and
//     the path to the file where the signature will be written) and
//   - one that verifies a file (taking as arguments the path to the file, the path to the RSA public key, and
//     the path to the signature file).
void problem_94_main(std::ostream& os) {
    using namespace tmcppc::crypto;

    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    const auto rsa_private_key_file_path{ fs::temp_directory_path() / "private_key.txt" };
    const auto rsa_public_key_file_path{ fs::temp_directory_path() / "public_key.txt" };
    const auto signature_file_path{ fs::temp_directory_path() / "signature.txt"};

    fmt::print(os, "Generating private and public key files\n\tPrivate key file: '{}'\n\tPublic key file: '{}'\n",
        rsa_private_key_file_path.generic_string(), rsa_public_key_file_path.generic_string());
    generate_keys(rsa_private_key_file_path, rsa_public_key_file_path);

    fmt::print(os, "Signing file with private key\n\tInput file: '{}'\n\tSignature file: '{}'\n",
        input_file_path.generic_string(), signature_file_path.generic_string());
    sign_file(input_file_path, rsa_private_key_file_path, signature_file_path);

    fmt::print(os, "Verifying file with public key\n");
    if (verify_file(input_file_path, rsa_public_key_file_path, signature_file_path)) {
        fmt::print(os, "\tOK\n");
    } else {
        fmt::print(os, "\tError: input file verification returned false\n");
    }
    fmt::print(os, "\n");
}
