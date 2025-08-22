#include <gtest/gtest.h>
#include "utils/atom_table.h"

using namespace cmulate;
TEST(AtomeTableBasics, CMulateTests)
{
  AtomTable at;
  std::string s1{"test string"};
  std::string s2{"test string"};
  AtomTable::Atom ret1{at.intern(s1)};
  AtomTable::Atom ret2{at.intern(s2)};
  EXPECT_EQ(ret1, ret2);
  std::string tmp{at.value(ret1)};
  EXPECT_EQ(tmp, s2);
  EXPECT_EQ(tmp, s1);
  tmp = at.value(ret2);
  EXPECT_EQ(tmp, s2);
  EXPECT_EQ(tmp, s1);
}

