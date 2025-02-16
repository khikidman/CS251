#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "include/search.h"

using namespace std;
using namespace testing;

map<string, set<string>> INDEX = {
  {"hello", {"example.com", "uic.edu"}},
  {"there", {"example.com"}},
  {"according", {"uic.edu"}},
  {"to", {"uic.edu"}},
  {"all", {"example.com", "uic.edu", "random.org"}},
  {"known", {"uic.edu"}},
  {"laws", {"random.org"}},
  {"of", {"random.org"}},
  {"aviation", {"random.org"}},
  {"a", {"uic.edu", "random.org"}},
};

TEST(CleanToken, BeginningAndEndPunct) {
  ASSERT_THAT(cleanToken(".HELLO."), StrEq("hello"));
  ASSERT_THAT(cleanToken("..heLlo..."), StrEq("hello"));
  ASSERT_THAT(cleanToken("!?hellO.\"!?"), StrEq("hello"));
  ASSERT_THAT(cleanToken(".\".HELLO.\"."), StrEq("hello"));
  ASSERT_THAT(cleanToken("...Hello..."), StrEq("hello"));
}

TEST(CleanToken, MiddleAndEndPunct) {
  ASSERT_THAT(cleanToken("HELLO.WORLD"), StrEq("hello.world"));
  ASSERT_THAT(cleanToken("HELLO.WORLD.!!"), StrEq("hello.world"));
  ASSERT_THAT(cleanToken("..heLlo...woRld"), StrEq("hello...world"));
  ASSERT_THAT(cleanToken("!?hellO.\"World!?"), StrEq("hello.\"world"));
}

TEST(GatherTokens, LeadingSpaces) {
  string text = "   Spaces with a leader will take over the world!";
  set<string> expected = {"spaces", "with", "a", "leader", "will", "take", "over", "the", "world"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, TrailingSpaces) {
  string text = "Who knew spaces could make trails?   ";
  set<string> expected = {"who", "knew", "spaces", "could", "make", "trails"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, MultipleSpacesBetweenWords) {
  string text = "how   many           spaces               are            there?";
  set<string> expected = {"how",    "many", "spaces", "are", "there"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(BuildIndex, TinyTxt) {
  string filename = "data/tiny.txt";
  map<string, set<string>> expectedIndex = {
      {"eggs", {"www.shoppinglist.com"}},
      {"milk", {"www.shoppinglist.com"}},
      {"fish", {"www.shoppinglist.com", "www.dr.seuss.net"}},
      {"bread", {"www.shoppinglist.com"}},
      {"cheese", {"www.shoppinglist.com"}},
      {"red", {"www.rainbow.org", "www.dr.seuss.net"}},
      {"gre-en", {"www.rainbow.org"}},
      {"orange", {"www.rainbow.org"}},
      {"yellow", {"www.rainbow.org"}},
      {"blue", {"www.rainbow.org", "www.dr.seuss.net"}},
      {"indigo", {"www.rainbow.org"}},
      {"violet", {"www.rainbow.org"}},
      {"one", {"www.dr.seuss.net"}},
      {"two", {"www.dr.seuss.net"}},
      {"i'm", {"www.bigbadwolf.com"}},
      {"not", {"www.bigbadwolf.com"}},
      {"trying", {"www.bigbadwolf.com"}},
      {"to", {"www.bigbadwolf.com"}},
      {"eat", {"www.bigbadwolf.com"}},
      {"you", {"www.bigbadwolf.com"}},
  };
  map<string, set<string>> studentIndex;
  int studentNumProcesed = buildIndex(filename, studentIndex);

  string indexTestFeedback =
      "buildIndex(\"" + filename + "\", ...) index incorrect\n";
  EXPECT_THAT(studentIndex, ContainerEq(expectedIndex)) << indexTestFeedback;

  string retTestFeedback =
      "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
  EXPECT_THAT(studentNumProcesed, Eq(4)) << retTestFeedback;
}

TEST(BuildIndex, FileNotFound) {
  string filename = "data/this_file_doesnt_exist.txt";
  map<string, set<string>> expectedIndex = {};
  map<string, set<string>> studentIndex;
  int studentNumProcesed = buildIndex(filename, studentIndex);

  string indexTestFeedback =
      "buildIndex(\"" + filename + "\", ...) index incorrect\n";
  EXPECT_THAT(studentIndex, ContainerEq(expectedIndex)) << indexTestFeedback;

  string retTestFeedback =
      "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
  EXPECT_THAT(studentNumProcesed, Eq(0)) << retTestFeedback;
}

TEST(FindQueryMatches, FirstTermNotInIndex) {
  set<string> expected;

  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, "supercalifragilistic"), ContainerEq(expected));

  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, "supercalifragilistic +hello"), ContainerEq(expected));

  expected = {"uic.edu"};
  EXPECT_THAT(findQueryMatches(INDEX, "supercalifragilistic known to"), ContainerEq(expected));

}

TEST(FindQueryMatches, LaterTermNotInIndex) {
  set<string> expected;

  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, "hello +supercalifragilistic"), ContainerEq(expected));

  expected = {"example.com", "uic.edu"};
  EXPECT_THAT(findQueryMatches(INDEX, "hello supercalifragilistic"), ContainerEq(expected));

  expected = {"example.com", "uic.edu", "random.org"};
  EXPECT_THAT(findQueryMatches(INDEX, "all -supercalifragilistic"), ContainerEq(expected));

}
