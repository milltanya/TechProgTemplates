//
// Created by akhtyamovpavel on 5/1/20.
//


#pragma once

#include <gtest/gtest.h>
#include <boost/filesystem/path.hpp>

#include "Tree.h"

class TreeTestCase : public ::testing::Test {
public:
    TreeTestCase();
    ~TreeTestCase() override;

protected:
    std::string test_data_path;
	FileNode a;
	FileNode b;
	FileNode c;
    FileNode dir;
    FileNode dir_dirs_only;
	FileNode test_data;
	FileNode test_data_dirs_only;
};
