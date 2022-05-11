#pragma once

#include "chapter_09_data_serialization/xml_movies.h"

#include <ostream>


void print_movies_released_after_year(std::ostream& os, const tmcppc::movies::xml::doc& doc, int year);
void print_last_actor_in_casting_list_for_every_movie(std::ostream& os, const tmcppc::movies::xml::doc& doc);

void problem_74_main(std::ostream& os);
void problem_74_main();
