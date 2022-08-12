#pragma once

#include <string>


namespace tmcppc::imap::samples::connector_response_text {
    static inline const std::string error{
        "Login denied"
    };
    static inline const std::string mailbox_folders{
        R"(* LIST (\HasNoChildren) "/" "test/tmcppc/problem_98")""\r\n"
    };
    static inline const std::string unread_email_ids{
        R"(* SEARCH 1)""\r\n"
    };
    static inline const std::string email{
        "MIME-Version: 1.0\r\n"
        "Date: Thu, 4 Aug 2022 16:28:32 +0200\r\n"
        "Message-ID: <CANF=GhQbSDK4ZgwNxkat3i0LQ_Y44t3iokHG8q_i-zDVFFAYsA@mail.gmail.com>\r\n"
        "Subject: =?UTF-8?Q?Harry_Potter=E2=80=99s_acceptance_letter_in_Harry_Potter_a?=\r\n"
        "\t=?UTF-8?Q?nd_the_Philosopher=E2=80=99s_Stone?=\r\n"
        "From: Roberto Turrado Camblor <rturrado@gmail.com>\r\n"
        "To: Roberto Turrado <rturrado@gmail.com>\r\n"
        "Content-Type: multipart/alternative; boundary=\"0000000000000ae13105e56b2abb\"\r\n"
        "\r\n"
        "--0000000000000ae13105e56b2abb\r\n"
        "Content-Type: text/plain; charset=\"UTF-8\"\r\n"
        "\r\n"
        "Dear Mr. Potter,\r\n"
        "\r\n"
        "We are pleased to inform you that you have been accepted at Hogwarts School\r\n"
        "of Witchcraft and Wizardry. Please find enclosed a list of all necessary\r\n"
        "books and equipment.\r\n"
        "\r\n"
        "Term begins on 1 September. We await your owl by no later than 31 July.\r\n"
        "\r\n"
        "Yours sincerely,\r\n"
        "Minerva McGonagall\r\n"
        "Deputy Headmistress\r\n"
        "\r\n"
        "--0000000000000ae13105e56b2abb\r\n"
        "Content-Type: text/html; charset=\"UTF-8\"\r\n"
        "Content-Transfer-Encoding: quoted-printable\r\n"
        "\r\n"
        "<div dir=3D\"ltr\">Dear Mr. Potter,<div><br>We are pleased to inform you that=\r\n"
        " you have been accepted at Hogwarts School of Witchcraft and Wizardry. Plea=\r\n"
        "se find enclosed a list of all necessary books and equipment.</div><div><br=\r\n"
        ">Term begins on 1 September. We await your owl by no later than 31 July.</d=\r\n"
        "iv><div><br>Yours sincerely,<br>Minerva McGonagall<br>Deputy Headmistress<b=\r\n"
        "r></div></div>\r\n"
        "\r\n"
        "--0000000000000ae13105e56b2abb--"
    };
    static inline const std::string email_subject{
        "Subject: =?UTF-8?Q?Harry_Potter=E2=80=99s_acceptance_letter_in_Harry_Potter_a?="
    };
}  // namespace tmcppc::imap::samples::connector_response_text
