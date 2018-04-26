//
// Created by joshua on 26.04.18.
//
#include <gtest/gtest.h>
#include "../LinkedList/LinkedList.h"

TEST(List, add)
{
  LinkedList<int> list;
  int a = 2;
  list.add(a);

  EXPECT_EQ(2, *list.get(0));
}