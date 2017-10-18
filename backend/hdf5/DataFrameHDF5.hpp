// Copyright (c) 2017, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.
//
// Authors: Christian Kellner <ckellner@redhat.com>

#ifndef NIX_DATA_FRAME_HDF5_H
#define NIX_DATA_FRAME_HDF5_H


#include <nix/NDSize.hpp>
#include <nix/base/IDataFrame.hpp>
#include "EntityWithSourcesHDF5.hpp"

namespace nix {
namespace hdf5 {

class DataFrameHDF5 : virtual public base::IDataFrame, public EntityWithSourcesHDF5 {
private:


public:

    /**
     * Standard constructor for existing DataFrames
     */
    DataFrameHDF5(const std::shared_ptr<base::IFile> &file, const std::shared_ptr<base::IBlock> &block, const H5Group &group);

    /**
     * Standard constructor for new DataFrames
     */
    DataFrameHDF5(const std::shared_ptr<base::IFile> &file, const std::shared_ptr<base::IBlock> &block, const H5Group &group, const std::string &id, const std::string &type, const std::string &name);

    /**
     * Standard constructor for new DataFrames that preserves the creation time.
     */
    DataFrameHDF5(const std::shared_ptr<base::IFile> &file, const std::shared_ptr<base::IBlock> &block, const H5Group &group, const std::string &id, const std::string &type, const std::string &name, time_t time);


    void createData(const std::vector<Column> &cols);

    std::vector<Column> columns() const override;

    std::vector<unsigned> nameToCol(const std::vector<std::string> &names) const;
    std::vector<std::string> colToName(const std::vector<unsigned> &cols) const;

    ndsize_t rows() const;
    void rows(ndsize_t n);

    void writeCells(ndsize_t row, const std::vector<Cell> &cells);
    void writeRow(ndsize_t row, const std::vector<Variant> &v);

    std::vector<Variant> readCells(ndsize_t row, const std::vector<std::string> &names) const;
    std::vector<Variant> readRow(ndsize_t row);

    void writeColumn(ndsize_t col,
                     ndsize_t offset,
                     ndsize_t count,
                     DataType dtype,
                     const char *data);

    void readColumn(ndsize_t col,
                    ndsize_t offset,
                    ndsize_t count,
                    DataType dtype,
                    void *data);

};


}
}

#endif
