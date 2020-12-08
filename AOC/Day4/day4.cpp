#include "day4.h"
#include <regex>

void Day4::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_4_input.txt");
  std::vector<std::string> passports {};
  std::vector<Passport> passports_structs {};
  std::string passport_line {};
  int valid_count = 0;

  for(std::string line; std::getline(file, line);)
  {
    if(line.empty())
    {
      passports.push_back(passport_line);
      passport_line = "";
      continue;
    }
    if(passport_line.length() > 0)
    {
      passport_line+= " ";
    }

    passport_line +=line;

  }
  passports.push_back(passport_line);
  file.close();

  const std::regex regex("([a-zA-Z0-9_]+):([^\r\n\t\f\v ]+)");

  for(const std::string p : passports)
  {
    Passport passport;
    std::smatch matches;
    std::string::const_iterator search(p.cbegin());
    while (std::regex_search(search, p.cend(), matches, regex))
    {
      if(matches[1].str() == "byr")
      {
        passport.byr = matches[2].str();
      }
      if(matches[1].str() == "iyr")
      {
        passport.iyr = matches[2].str();
      }
      if(matches[1].str() == "eyr")
      {
        passport.eyr = matches[2].str();
      }
      if(matches[1].str() == "hgt")
      {
        passport.hgt = matches[2].str();
      }
      if(matches[1].str() == "hcl")
      {
        passport.hcl = matches[2].str();
      }
      if(matches[1].str() == "ecl")
      {
        passport.ecl = matches[2].str();
      }
      if(matches[1].str() == "pid")
      {
        passport.pid = matches[2].str();
      }
      if(matches[1].str() == "cid")
      {
        passport.cid = matches[2].str();
      }
      search = matches.suffix().first;
    }
    passports_structs.push_back(passport);
  }

  int valid_advanced_count = 0;
  for(Passport p : passports_structs)
  {
    if(checkPassport(p))
    {
      valid_count++;
    }
    if(checkPassport_advanced(p))
    {
      valid_advanced_count++;
    }
  }

  std::cout<<"Valid passports: "<<valid_count<<std::endl;
  std::cout<<"Valid advanced passports: "<<valid_advanced_count<<std::endl;
}

bool Day4::checkPassport(Passport passport)
{
  return !(passport.byr.empty() || passport.iyr.empty() || passport.eyr.empty() || passport.hgt.empty() || passport.hcl.empty() || passport.ecl.empty() || passport.pid.empty());
}

bool Day4::checkPassport_advanced(Passport passport)
{
  bool all_fields_present = !(passport.byr.empty() || passport.iyr.empty() || passport.eyr.empty() || passport.hgt.empty() || passport.hcl.empty() || passport.ecl.empty() || passport.pid.empty());
  bool byr_valid = passport.byr.length() == 4 && stoi(passport.byr) >= 1920 && stoi(passport.byr) <= 2002;
  bool iyr_valid = passport.iyr.length() == 4 && stoi(passport.iyr) >= 2010 && stoi(passport.iyr) <= 2020;
  bool eyr_valid = passport.eyr.length() == 4 && stoi(passport.eyr) >= 2020 && stoi(passport.eyr) <= 2030;
  bool hgt_valid = false;
  if (passport.hgt.c_str()[passport.hgt.size()-1] == 'm')
  {
    if(stoi(passport.hgt.substr(0,3)) >= 150 && stoi(passport.hgt.substr(0,3)) <= 193)
    {
    hgt_valid = true;
    }
  }
  if (passport.hgt.c_str()[passport.hgt.size()-1] == 'n')
  {
    if(stoi(passport.hgt.substr(0,2)) >= 59 && stoi(passport.hgt.substr(0,2)) <= 76)
    {
      hgt_valid = true;
    }
  }
  bool hcl_valid = false;
  bool broken = false;
  if(passport.hcl.size() == 7)
  {
    if(passport.hcl.c_str()[0] == '#')
    {
      for(int i = 1; i < passport.hcl.size();i++)
      {
        if(!islower(passport.hcl.c_str()[i]) && !isdigit(passport.hcl.c_str()[i]))
        {
          broken = true;
          break;
        }
      }
      hcl_valid = !broken;
    }
  }
  bool ecl_valid = passport.ecl == "amb" || passport.ecl == "blu" || passport.ecl == "brn" || passport.ecl == "gry" || passport.ecl == "grn" || passport.ecl == "hzl" || passport.ecl == "oth";
  bool pid_valid = true;
  if(passport.pid.size() != 9)
  {
    pid_valid = false;
  }
  if(pid_valid)
  {
    for (int i = 0; i < passport.pid.size(); i++){
      if(!isdigit(passport.pid.c_str()[i])){
        pid_valid = false;
        break;
      }
    }
  }
  return all_fields_present && byr_valid && iyr_valid && eyr_valid && hgt_valid && hcl_valid && ecl_valid && pid_valid;
}