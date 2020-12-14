#include "day14.h"

void Day14::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_14_input.txt");

  std::unordered_map<long long, long long> memory;
  std::unordered_map<long long, long long> memory2;
  std::string current_mask;

  for (std::string line; std::getline(file, line);) {

    if(line[1] == 'a')
    {
      std::stringstream parser(line);
      parser.ignore(7);
      parser >> current_mask;
    }
    else
    {
      long long address;
      long long value;
      line.erase(line.find(']'),1);

      std::stringstream parser(line);
      parser.ignore(4);

      std::string address_string;
      parser >> address_string;
      address = stoll(address_string);

      std::vector<long long> addresses_modified = decipher2(current_mask, address);
      parser.ignore(3);

      std::string value_string;
      parser >> value_string;
      value = stoll(value_string);

      long long value_modified = decipher(current_mask, value);

      memory[address] = value_modified;
      for(long long address_modified : addresses_modified) memory2[address_modified] = value;
    }
  }

  long long sum = 0;
  long long sum2 = 0;
    for(std::unordered_map<long long, long long>::iterator it = memory.begin(); it !=memory.end(); it++)
    {
      sum+=it->second;
    }

  for(std::unordered_map<long long, long long>::iterator it = memory2.begin(); it !=memory.end(); it++)
  {
    sum2+=it->second;
  }

    std::cout<<"Result 1 : "<<sum<<std::endl;

  std::cout<<"Result 2 : "<<sum2<<std::endl;
}


long long Day14::decipher(std::string mask, long long entry)
{
  long long output = 0;

  std::string binary_entry = "";

  while(entry > 0)
  {
    char c = entry%2 ? '1' : '0';
    entry /= 2;
    binary_entry += c;
  }
  int n =binary_entry.size()-1;
  for(int i=0;i<(binary_entry.size()/2);i++){
    std::swap(binary_entry[i],binary_entry[n]);
    n = n-1;
  }

  std::string binary_entry_full = binary_entry;
  for(int i = 0; i < mask.size() - binary_entry.size(); i++){
    binary_entry_full.insert(binary_entry_full.begin(),'0');
  }

  for(int i = 0; i < binary_entry_full.size(); i++)
  {
    if(mask[i] == 'X') continue;
    binary_entry_full[i] = mask[i];
  }

  long long base = 1;
  for(int i = binary_entry_full.size()-1; i >= 0; i--)
  {
    if(binary_entry_full[i] == '1') output+=base;

    base*=2;
  }
  return output;
}

std::vector<long long> Day14::decipher2(std::string mask, long long entry)
{
  std::vector<long long> output;

  std::string binary_entry = "";

  while(entry > 0)
  {
    char c = entry%2 ? '1' : '0';
    entry /= 2;
    binary_entry += c;
  }
  int n =binary_entry.size()-1;
  for(int i=0;i<(binary_entry.size()/2);i++){
    std::swap(binary_entry[i],binary_entry[n]);
    n = n-1;
  }

  std::string binary_entry_full = binary_entry;
  for(int i = 0; i < mask.size() - binary_entry.size(); i++){
    binary_entry_full.insert(binary_entry_full.begin(),'0');
  }

  for(int i = 0; i < binary_entry_full.size(); i++)
  {
    if(mask[i] == '0') continue;
    if(mask[i] == 'X') binary_entry_full[i]= '0';
    if(mask[i] == '1')binary_entry_full[i] = '1';
  }

  long long address_modified = 0;
  long long base = 1;
  for(int i = binary_entry_full.size()-1; i >= 0; i--)
  {
    if(binary_entry_full[i] == '1') address_modified+=base;

    base*=2;
  }

  output.push_back(address_modified);
  for(int i = mask.size()-1; i >= 0; i--)
  {
    if(mask[i] == 'X')
    {
      std::vector<long long> output_snapshot = output;
      for(long long l : output_snapshot)
      {
        output.push_back(l + pow(2,mask.size()-1-i));
      }
    }
  }
  return output;
}

