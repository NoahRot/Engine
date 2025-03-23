#include "Tools/data_file.hpp"

namespace ora {

DataNode::DataNode()
: content("")
{}

DataNode::DataNode(const std::string& content_)
: content(content_)
{}

bool DataNode::has_content() const {
    return content != "";
}

DataNode& DataNode::operator[](const std::string& name) {
    return children[name];
}

DataNode& DataNode::operator[](const char* name) {
    return children[std::string(name)];
}

DataNode& DataNode::operator=(const std::string& str) {
    content = str;
    return *this;
}

DataNode::operator std::string() {
    return content;
}

DataNode& DataNode::operator=(int value) {
    content = std::to_string(value);
    return *this;
}

DataNode::operator int() {
    int result(0);
    try {
        result = std::stoi(content);
    }catch(const std::invalid_argument&) {
        std::cout << "CONVERSION ERROR TO INT : " << content << std::endl;
    } 
    return result;
}

DataNode& DataNode::operator=(uint32_t value) {
    content = std::to_string(value);
    return *this;
}

DataNode::operator uint32_t() {
    uint32_t result(0);
    try {
        result = static_cast<uint32_t>(std::stoul(content));
    }catch(const std::invalid_argument&) {
        std::cout << "CONVERSION ERROR TO UINT32_T : " << content << std::endl;
    } 
    return result;
}

DataNode& DataNode::operator=(float value) {
    content = std::to_string(value);
    return *this;
}

DataNode::operator float() {
    float result(0.0f);
    try {
        result = std::stof(content);
    }catch(const std::invalid_argument&) {
        std::cout << "CONVERSION ERROR TO FLOAT : " << content << std::endl;
    } 
    return result;
}

DataNode& DataNode::operator=(double value) {
    content = std::to_string(value);
    return *this;
}

DataNode::operator double() {
    double result(0.0f);
    try {
        result = std::stod(content);
    }catch(const std::invalid_argument&) {
        std::cout << "CONVERSION ERROR TO DOUBLE : " << content << std::endl;
    } 
    return result;
}





DataFile::DataFile()
{}

DataFile::DataFile(const DataNode& node) 
: m_root(node)
{}

DataFile::DataFile(const std::string& path) {
    load_txt(path);
}

DataNode& DataFile::get() {
    return m_root;
}

bool DataFile::save_txt(const std::string& path) {
    // Open file
    std::fstream file;
    file.open(path, std::ios::out);
    if (!file.is_open()) {
        Logger::instance().log(Error, "Datafile can not save into file : " + path);
        return false;
    }

    // Write data
    write_txt(m_root, 0, file);
    file.close();

    return true;
}

bool DataFile::load_txt(const std::string& path) {
    // Open file
    std::fstream file;
    file.open(path, std::ios::in);
    if (!file.is_open()) {
        Logger::instance().log(Error, "Datafile can not load into file : " + path);
        return false;
    }

    // Write data
    read_txt(file);
    file.close();

    return true;
}

void DataFile::write_txt(const DataNode& node, int depth, std::fstream& stream) {
    // Build depth string
    std::string depth_str;
    for (int i(0) ; i < depth ; ++i) {
        depth_str += " ";
    }

    // Save the data and recursively call write
    for (const auto& n : node.children) {
        stream << depth_str << n.first << ":" << n.second.content << "\n";
        write_txt(n.second, depth + 1, stream);
    }
}

void DataFile::read_txt(std::fstream& stream) {

    std::string line;
    std::stack<std::pair<int, DataNode*>> stacker;

    // Reset node
    m_root = DataNode();
    stacker.push({-1, &m_root});

    // read stream
    while(stream) {
        std::getline(stream, line);

        // Compute depth
        size_t depth(0);
        while (depth < line.size() && line[depth] == ' ') {
            ++depth;
        }

        // Create sub string and get the data
        std::string sub_string = line.substr(depth);
        size_t separator = sub_string.find(':');

        // Check that the separator has been found
        if (separator != std::string::npos) {
        
            // Check if the data can be obtained correctly
            std::string name = sub_string.substr(0, separator);
            std::string content = sub_string.substr(separator+1);

            // Find the parent
            while (!stacker.empty() && stacker.top().first >= (int)depth) {
                stacker.pop();
            }

            // Add the node
            DataNode* parent = stacker.top().second;
            (*parent)[name] = content;
            stacker.push({depth, &((*parent)[name])});

        }
    }
}

}