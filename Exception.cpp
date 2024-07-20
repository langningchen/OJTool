/**********************************************************************
OJTool: Get problem and submit code for OJ just from your CLI!
Copyright (C) 2024  langningchen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
**********************************************************************/

#include <Exception.hpp>
Exception::Exception() {
}
Exception::Exception(const std::string &Message) {
    Content = "We're sorry but an error occurred " + Message + "\n" +
              "\n" +
              "Please try to run this program again later, if this error still occurrs, contact the developer for help! Thanks! \n";
}
std::string Exception::what() const {
    return Content;
}
Exception::~Exception() {
}
