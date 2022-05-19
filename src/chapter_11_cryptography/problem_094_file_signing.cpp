#include "chapter_11_cryptography.h"

#include <filesystem>
#include <format>
#include <iostream>  // cout

#include "cryptocpp/osrng.h"  // AutoSeededRandomPool
#include "cryptocpp/rsa.h"  // RSAES_OAEP_SHA_Decryptor, RSAES_OAEP_SHA_Encryptor, RSASSA_PKCS1v15_SHA_Signer, RSASSA_PKCS1v15_SHA_Verifier
#include "cryptocpp/files.h"  // FileSink, FileSource
#include "cryptocpp/hex.h"  // HexDecoder, HexEncoder

namespace fs = std::filesystem;


void generate_keys(const fs::path& rsa_private_key_file_path, const fs::path& rsa_public_key_file_path)
{
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


void sign_file(const fs::path& input_file_path, const fs::path& rsa_private_key_file_path, const fs::path& signature_file_path)
{
    using namespace CryptoPP;

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


bool verify_file(const fs::path& input_file_path, const fs::path& rsa_public_key_file_path, const fs::path& signature_file_path)
{
    using namespace CryptoPP;

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


// File signing
//
// Write a program that is able to sign files and verify that a signed file has not been tampered with, using RSA cryptography.
// When signing a file, the signature should be written to a separate file and used later for the verification process.
// The program should provide at least two functions:
//   - one that signs a file (taking as arguments the path to the file, the path to the RSA private key, and
//     the path to the file where the signature will be written) and
//   - one that verifies a file (taking as arguments the path to the file, the path to the RSA public key, and
//     the path to the signature file).
void problem_94_main()
{
    const auto input_file_path{ fs::current_path() / "res" / "fonts" / "calibri.ttf" };
    const auto rsa_private_key_file_path{ fs::temp_directory_path() / "private_key.txt" };
    const auto rsa_public_key_file_path{ fs::temp_directory_path() / "public_key.txt" };
    const auto signature_file_path{ fs::temp_directory_path() / "signature.txt"};

    std::cout << std::format("Generating private and public key files\n\tPrivate key file: '{}'\n\tPublic key file: '{}'\n",
        rsa_private_key_file_path.generic_string(), rsa_public_key_file_path.generic_string());
    generate_keys(rsa_private_key_file_path, rsa_public_key_file_path);

    std::cout << std::format("Signing file with private key\n\tInput file: '{}'\n\tSignature file: '{}'\n",
        input_file_path.generic_string(), signature_file_path.generic_string());
    sign_file(input_file_path, rsa_private_key_file_path, signature_file_path);

    std::cout << "Verifying file with public key\n";
    if (verify_file(input_file_path, rsa_public_key_file_path, signature_file_path)) {
        std::cout << "\tOK\n";
    }
    else {
        std::cout << "\tError: input file verification returned false\n";
    }
    std::cout << "\n";
}
