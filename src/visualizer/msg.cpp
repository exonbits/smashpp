#include "msg.h"
#include <stdio.h>
#include <stdlib.h>
using namespace smashpp;

void smashpp::print_menu_visual () {
  cerr <<
    "Usage: visualizer-visual [OPTION]... [FILE]                             \n"
    "Visualization of visualizer-map output.                                 \n"
    "                                                                        \n"
    "Non-mandatory arguments:                                                \n"
    "                                                                        \n"
    "  -h                         give this help,                            \n"
    "  -V                         display version number,                    \n"
    "  -v                         verbose mode (more information),           \n"
    "  -l <link>                  link type between maps [0;4],              \n"
    "  -w <width>                 image sequence width,                      \n"
    "  -s <space>                 space between sequences,                   \n"
    "  -m <mult>                  color id multiplication factor,            \n"
    "  -b <begin>                 color id beggining,                        \n"
    "  -c <minimum>               minimum block size to consider,            \n"
    "  -i                         do NOT show inversion maps,                \n"
    "  -r                         do NOT show regular maps,                  \n"
    "  -o <FILE>                  output image filename with map,            \n"
    "                                                                        \n"
    "Mandatory arguments:                                                    \n"
    "                                                                        \n"
    "  <FILE>                     filename with positions from the           \n"
    "                             visualizer-map program (*.pos),            \n"
    "                                                                        \n"
    "Report bugs to <pratas@ua.pt>."                                     <<endl;
}

void smashpp::print_version () {
  cerr <<
    "                                                                        \n"
    "                         =====================                          \n"
    "                         |   ELEANORA v"
    <<VERSION_eleanora<<"."<<RELEASE_eleanora<<"   |                         \n"
    "                         =====================                          \n"
    "                                                                        \n"
    "                  Ultra-fast mapping and visualization                  \n"
    "                       of similar genomic regions                       \n"
    "                                                                        \n"
    "                  It includes the following programs:                   \n"
    "                           * visualizer-map                             \n"
    "                           * visualizer-visual                          \n"
    "                                                                        \n"
    "Copyright (C) 2015-2018 University of Aveiro. This is a Free software.  \n"
    "You may redistribute copies of it under the terms of the GNU - General  \n"
    "Public License v3 <http://www.gnu.org/licenses/gpl.html>. There is NOT  \n"
    "ANY WARRANTY, to the extent permitted by law. Developed and Written by  \n"
    "Diogo Pratas.\n"                                                    <<endl;
}