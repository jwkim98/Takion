#include <iostream>
#include <doctest.h>

#include <CubbyDNN/Datas/Dataset/MNISTDataset.hpp>

#include <filesystem>

using namespace CubbyDNN;

TEST_CASE("[MNISTDataset] - Load Train Set")
{
    MNISTDataset dset("./mnist", true);

    CHECK_EQ(dset.IsTrain(), true);

    CHECK_EQ(dset.GetSize(), 60000llu);

    auto [img, target] = dset.Get(0);
    CHECK_EQ(img.GetHeight(), 28);
    CHECK_EQ(img.GetWidth(), 28);
    CHECK_EQ(img.IsGrayScale(), true);
    CHECK_EQ(target < 10, true);
}

TEST_CASE("[MNISTDataset] - Load Test Set")
{
    MNISTDataset dset("./mnist", false);

    CHECK_EQ(dset.IsTrain(), false);

    CHECK_EQ(dset.GetSize(), 10000llu);

    auto [img, target] = dset.Get(0);
    CHECK_EQ(img.GetHeight(), 28);
    CHECK_EQ(img.GetWidth(), 28);
    CHECK_EQ(img.IsGrayScale(), true);
    CHECK_EQ(target < 10, true);
}