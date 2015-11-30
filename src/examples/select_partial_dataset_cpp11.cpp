#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include <highfive/H5File.hpp>
#include <highfive/H5DataSpace.hpp>
#include <highfive/H5DataSet.hpp>


const std::string FILE_NAME("select_partial_example.h5");
const std::string DATASET_NAME("dset");

// Create a dataset name "dset" of double 4x6
//
int main (void)
{
    using namespace HighFive;
    try
    {
        // Create a new file using the default property lists.
        File file(FILE_NAME, File::ReadWrite | File::Create | File::Truncate);

        // we have some example values in a 2D vector 2x5
        std::vector<std::vector<double> > values = { {1.0, 2.0, 4.0, 8.0, 16.0},
                                                    {32.0, 64.0, 128.0, 256.0, 512.0} };

        // lets create a dataset of this size and write them
        DataSet dataset = file.createDataSet<double>(DATASET_NAME,  DataSpace::From(values));
        dataset.write(values);

        // now we read back 2x2 values after an offset of 0x1
        std::vector<std::vector<double> > result;
        dataset.select({0, 1}, {2, 2}).read(result);

        // we print out 4 values
        for(auto i : result){
            for(auto j: i){
                std::cout << " " << j;
            }
            std::cout << "\n";
        }

    }catch(Exception & err){
        // catch and print any HDF5 error
        std::cerr << err.what() << std::endl;
    }

    return 0;  // successfully terminated
}

