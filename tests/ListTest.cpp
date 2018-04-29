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
  list.add(5);
  list.add(10);

  EXPECT_EQ(2, list.get(0));
  EXPECT_EQ(5, list.get(1));
  EXPECT_EQ(10, list.get(2));
}

TEST(List, remove)
{
  LinkedList<int> list;

  list.add(5);
  list.add(10);

  try
  {
    EXPECT_EQ(2, list.size());
    EXPECT_EQ(10, list.remove(1));
    EXPECT_EQ(5, list.get(0));
  } catch (range_error &e) {
    cout << "LOL";
  }

}

/*TEST(List, getNode)
{
  LinkedList<int> list;

  list.add(5);
  list.add(10);
  list.add(12);

  try
  {
    EXPECT_EQ(3, list.size());
    EXPECT_EQ(10, list.getNode(1)->object);
    EXPECT_EQ(5, list.getNode(0)->object);
    EXPECT_EQ(12, list.getNode(2)->object);
  } catch (range_error &e) {
    cout << "LOL";
  }

}*/

TEST(List, getID)
{
  LinkedList<int> list;

  list.add(5);
  list.add(10);
  list.add(12);

  EXPECT_EQ(0, list.getID(5));
  EXPECT_EQ(1, list.getID(10));
  EXPECT_EQ(2, list.getID(12));
}