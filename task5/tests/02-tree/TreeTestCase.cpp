//
// Created by akhtyamovpavel on 5/1/20.
//


#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include "TreeTestCase.h"
#include "Tree.h"

TreeTestCase::TreeTestCase() {
    test_data_path = "test_data";
    while (boost::filesystem::exists(test_data_path)) {
        test_data_path += "_";
    }

    // test_data
    // ├── a
    // ├── b
    // └── dir
    //     └── c
    boost::filesystem::create_directory(test_data_path);
    boost::filesystem::create_directory(test_data_path + "/dir");
    boost::filesystem::ofstream a_stream(test_data_path + "/a");
    a_stream.close();
    boost::filesystem::ofstream b_stream(test_data_path + "/b");
    b_stream.close();
    boost::filesystem::ofstream c_stream(test_data_path + "/dir/c");
    c_stream.close();

    a = {"a", false, {}};
    b = {"b", false, {}};
    c = {"c", false, {}};
    dir = {"dir", true, {c}};
    dir_dirs_only = {"dir", true, {}};
    test_data = {test_data_path, true, {dir, a, b}};
    test_data_dirs_only = {test_data_path, true, {dir_dirs_only}};
}

TreeTestCase::~TreeTestCase() {
    boost::filesystem::remove_all(test_data_path);
}

TEST_F(TreeTestCase, DoesntExist) {
    ASSERT_THROW(GetTree(test_data_path + "/some_directory", false), std::invalid_argument);
}

TEST_F(TreeTestCase, NotADirectory) {
    ASSERT_THROW(GetTree(test_data_path + "/a", false), std::invalid_argument);
}

TEST_F(TreeTestCase, SmallDirectoryDirsOnly) {
    ASSERT_EQ(GetTree(test_data_path + "/dir", true), dir_dirs_only);
}

TEST_F(TreeTestCase, SmallDirectory) {
    ASSERT_EQ(GetTree(test_data_path + "/dir", false), dir);
}

TEST_F(TreeTestCase, BigDirectoryDirsOnly) {
    ASSERT_EQ(GetTree("test_data", true), test_data_dirs_only);
}

TEST_F(TreeTestCase, BigDirectory) {
    FileNode expected = test_data;
    FileNode actual = GetTree("test_data", false);

    std::vector<size_t> perm = {0, 1, 2};
    while (!(actual == expected)) {
        std::next_permutation(perm.begin(), perm.end());
        expected.children = {expected.children[perm[0]], expected.children[perm[1]], expected.children[perm[2]]};
    }
    ASSERT_EQ(actual, expected);
}
