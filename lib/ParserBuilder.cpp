#include "ParserBuilder.hpp"
#include <stdexcept>
#include <utility>

namespace SageParser
{

    void ParserBuilder::setReader(std::unique_ptr<IReader> reader)
    {
        reader_ = std::move(reader);
    }

    void ParserBuilder::setProcessors(std::vector<std::unique_ptr<IProcessor>> processors)
    {
        processors_ = std::move(processors);
    }

    void ParserBuilder::setWriter(std::unique_ptr<IWriter> writer)
    {
        writer_ = std::move(writer);
    }

    void ParserBuilder::performOperation()
    {
        if (!reader_)
            throw std::runtime_error("ParserBuilder error: Reader is not set.");

        if (!writer_)
            throw std::runtime_error("ParserBuilder error: Writer is not set.");

        // Reading the table from file
        auto table = reader_->read();

        // Using cascade of preset processors
        for (auto &processor : processors_)
            table = processor->process(table);

        // Writing table to the file
        writer_->write(table);
    }
}
