#include "Tools/xml_manager.hpp"

XML_Node::XML_Node()
: content(""), parent(nullptr)
{}

XML_Node::XML_Node(const std::string& title_, const std::string& content_, XML_Node* parent_)
: title(title_), content(content_), parent(parent_)
{}

XML_Node* XML_Node::get(const std::string& title) {
    for (size_t i(0) ; i < children.size() ; ++i) {
        if (children[i].title == title) {
            return &children[i];
        }
    }

    return nullptr;
}

std::string XML_Node::get_string() {
    return content;
}

int XML_Node::get_int() {
    return std::stoi(content);
}

uint32_t XML_Node::get_uint32() {
    return std::stoul(content);
}

float XML_Node::get_float() {
    return std::stof(content);
}

double XML_Node::get_double() {
    return std::stod(content);
}

bool XML_Node::get_bool() {
    if (content == "true") {
        return true;
    }else if(content == "false") {
        return false;
    }else{
        return std::stoi(content);
    }
}

XML_Node* XML_Node::begin() {
    return &children.front();
}

XML_Node* XML_Node::end() {
    return &children.front() + children.size();
}

const XML_Node* XML_Node::begin() const {
    return &children.front();
}

const XML_Node* XML_Node::end() const {
    return &children.front() + children.size();
}





XML_Mapping& XML_Mapping::operator[](const std::string& str) {
    return map[str];
}

bool XML_Mapping::validity(const std::string& str) {
    return map.find(str) != map.end();
}

std::string XML_Mapping::get_string() {
    return content;
}

int XML_Mapping::get_int() {
    return std::stoi(content);
}

uint32_t XML_Mapping::get_uint32() {
    return std::stoul(content);
}

float XML_Mapping::get_float() {
    return std::stof(content);
}

double XML_Mapping::get_double() {
    return std::stod(content);
}

bool XML_Mapping::get_bool() {
    if (content == "true") {
        return true;
    }else if(content == "false") {
        return false;
    }else{
        return std::stoi(content);
    }
}





XML_Manager::iterator XML_Manager::begin() {
    return &m_init_nodes.front();
}

XML_Manager::iterator XML_Manager::end() {
    return &m_init_nodes.front() + m_init_nodes.size();
}

XML_Manager::const_iterator XML_Manager::begin() const {
    return &m_init_nodes.front();
}

XML_Manager::const_iterator XML_Manager::end() const {
    return &m_init_nodes.front() + m_init_nodes.size();
}

XML_Manager::XML_Manager()
:m_error("None")
{}

std::string XML_Manager::get_error() {
    return m_error;
}

bool XML_Manager::read(const std::string& path) {
    std::ofstream file(path, std::ios::in);
    if (file && file.is_open()) {
        bool read_result = read_content(file);
        file.close();
        return read_result;

    }else{
        m_error = "Can not open file : " + path;
        return false;
    }
}

void XML_Manager::print() {
    for (const auto& n : m_init_nodes) {
        print_recursive(n, 0);
    }
}

XML_Node* XML_Manager::get(const std::string& title) {
    for (size_t i(0) ; i < m_init_nodes.size() ; ++i) {
        if (m_init_nodes[i].title == title) {
            return &m_init_nodes[i];
        }
    }

    return nullptr;
}

void XML_Manager::push_root_node(const XML_Node& node) {
    m_init_nodes.push_back(node);
}

void XML_Manager::reset() {
    m_init_nodes = {};
}

bool XML_Manager::save(const std::string& path) {
    std::ofstream save_file(path, std::ios::out);

    if (!save_file.is_open()) {
        m_error = "Can not open save file : " + path;
        return false;
    } 

    save_file << "<?xml version=\"1.0\"?>\n";
    for (const auto& i : m_init_nodes) {
        write(i, save_file, 0);
    }

    save_file.close();

    return true;
}

XML_Mapping XML_Manager::get_map() {
    XML_Mapping initial;

    for (const auto& i : m_init_nodes) {
        initial.map[i.title] = build_map(i);
    }

    return initial;
}

void XML_Manager::load_map(const XML_Mapping& map, int depth) {
    reset();

    for (const auto& i : map.map) {
        XML_Node node;
        node.title = i.first;
        node.content = i.second.content;
        node.parent = nullptr;

        build_from_map(node, i.second);

        m_init_nodes.push_back(node);
    }
}

void XML_Manager::build_from_map(XML_Node& parent, const XML_Mapping& map) {
    for (const auto& i : map.map) {
        XML_Node node;
        node.title = i.first;
        node.content = i.second.content;
        node.parent = &parent;

        build_from_map(node, i.second);

        parent.children.push_back(node);
    }
}

XML_Mapping XML_Manager::build_map(const XML_Node& node) {
    XML_Mapping initial;

    initial.content = node.content;

    for (const auto& i : node.children) {
        initial.map[i.title] = build_map(i);
    }

    return initial;
}

void XML_Manager::write(const XML_Node& node, std::ofstream& stream, int depth) {
    std::string depth_str = "";
    for (int i(0) ; i < depth ; ++i) {
        depth_str += "  ";
    }

    if (node.children.size() == 0) {
        stream  << depth_str << "<" << node.title << ">" << node.content  << "</" << node.title << ">\n";        

    }else{
        stream << depth_str << "<" << node.title << ">\n";

        for (const auto& i : node.children) {
            write(i, stream, depth + 1);
        }

        stream << depth_str << "</" << node.title << ">\n";
    }
}

bool XML_Manager::read_content(std::ofstream& file) {

    // Load the file
    std::stringstream stream;
    stream << file.rdbuf();
    std::string xml_str = stream.str();

    // Create the Node System
    m_init_nodes = std::vector<XML_Node>();
    XML_Node* current_node(nullptr);

    for (size_t i(0) ; i < xml_str.size() ; ++i) {
        char c = xml_str[i];

        // Check open/close balise
        if (c == '<') {

            // Case close balise
            if (xml_str[i+1] == '/') {

                // Check that file do not stop too early
                if (i + 2 >= xml_str.size()) {
                    m_error = "File stop in the middle of a balise";
                    return false;
                }

                i += 2;
                std::pair<std::string, bool> pair = read_balise(i, xml_str);
                if (!pair.second) {
                    return false;
                }
                std::string title = pair.first;

                // Check that we close the correct balise
                if (current_node && title == current_node->title) {
                    current_node = current_node->parent;

                }else{
                    m_error = "Close balise do not match open balise : " + title + " =! " + current_node->title;
                    return false;
                }

            // Balise not important
            }else if(xml_str[i+1] == '?' || xml_str[i+1] == '!'){

                // Check that file do not stop too early
                if (i + 2 >= xml_str.size()) {
                    m_error = "File stop in the middle of a balise";
                    return false;
                }

                i += 2;
                read_balise(i, xml_str);
            
            // Case open Balise
            }else{

                // Check that file do not stop too early
                if (i + 1 >= xml_str.size()) {
                    m_error = "File stop in the middle of a balise";
                    return false;
                }

                i += 1;
                std::pair<std::string, bool> pair = read_balise(i, xml_str);
                if (!pair.second) {
                    return false;
                }
                std::string title = pair.first;
                
                if (current_node) {
                    current_node->content = "";
                }

                // Case new node children of another node
                if (current_node) {
                    size_t index_tmp = current_node->children.size();
                    current_node->children.push_back(XML_Node());

                    current_node->children[index_tmp].parent = current_node;
                    current_node->children[index_tmp].title = title;

                    current_node = &current_node->children[index_tmp];
                
                // Case new node root node
                }else{
                    size_t index_tmp = m_init_nodes.size();
                    m_init_nodes.push_back(XML_Node());

                    m_init_nodes[index_tmp].parent = nullptr;
                    m_init_nodes[index_tmp].title = title;

                    current_node = &m_init_nodes[index_tmp];
                }
            }
        
        // Content of a balise
        }else{
            if (current_node && c != '\n') {
                current_node->content += c;
            }
        }
    }

    return true;
}

std::pair<std::string, bool> XML_Manager::read_balise(size_t& i, std::string& xml_str) {
    std::string name("");           // name of the balise
    bool is_reading_title(true);    // is it always the name of a parameter

    while (xml_str[i] != '>') {

        // Check length
        if (i >= xml_str.size()) {
            m_error = "File stop in the middle of a balise";
            return {"", false};
        }

        // Stop the title reading
        if (xml_str[i] == ' ') { 
            is_reading_title = false;
        }

        // Reading the title
        if (is_reading_title){
            name += xml_str[i];
        }

        ++i;
    }

    return {name, true};
}

void XML_Manager::print_recursive(const XML_Node& node, int depth) {
    for (int i(0) ; i < depth ; ++i) {
        std::cout << "-";
    }
    std::cout << "<" << node.title << "> : " << node.content << std::endl;

    for (const auto& n : node.children) {
        print_recursive(n, depth + 1);
    }
}