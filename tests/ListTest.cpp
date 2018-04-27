//
// Created by joshua on 26.04.18.
//
#include <gtest/gtest.h>
#include "../LinkedList/LinkedList.h"

TEST(List, add)
{
  LinkedList<int> list;
  int &a = *(int*)malloc(sizeof(int));
  a = 2;
  list.add(a);

  EXPECT_EQ(2, *list.get(0));
}

TEST(List, remove)
{
  LinkedList<int> list;
  int &a = *(int*)malloc(sizeof(int));
  list.add(a);
  int &b = *(int*)malloc(sizeof(int));
  list.add(b);

  EXPECT_EQ(2, list.size());
  list.remove(0);
  EXPECT_EQ(2, *list.get(3));
}