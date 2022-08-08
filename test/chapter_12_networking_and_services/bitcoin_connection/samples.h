#pragma once

#include <string>


namespace tmcppc::bitcoin {
    namespace samples {
        static inline const std::string connector_adaptor_response{
            "{\n"
            "  \"EUR\": {\n"
            "    \"15m\": 22777.77,\n"
            "    \"last\": 22777.77,\n"
            "    \"buy\": 22777.77,\n"
            "    \"sell\": 22777.77,\n"
            "    \"symbol\": \"EUR\"\n"
            "  },\n"
            "  \"GBP\": {\n"
            "    \"15m\": 19210.63,\n"
            "    \"last\": 19210.63,\n"
            "    \"buy\": 19210.63,\n"
            "    \"sell\": 19210.63,\n"
            "    \"symbol\": \"GBP\"\n"
            "  },\n"
            "  \"USD\": {\n"
            "    \"15m\": 23187.23,\n"
            "    \"last\": 23187.23,\n"
            "    \"buy\": 23187.23,\n"
            "    \"sell\": 23187.23,\n"
            "    \"symbol\": \"USD\"\n"
            "  }\n"
            "}\n" };
    }  // namespace samples
}  // namespace tmcppc::bitcoin
