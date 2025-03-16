#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <inttypes.h>

struct XML_Node {
    std::string title;
    std::string content;
    XML_Node* parent;
    std::vector<XML_Node> children;

    XML_Node();

    XML_Node(const std::string& title_, const std::string& content_, XML_Node* parent_);

    XML_Node* get(const std::string& title);

    std::string get_string();

    int get_int();

    uint32_t get_uint32();

    float get_float();

    double get_double();

    bool get_bool();

    XML_Node* begin();

    XML_Node* end();

    const XML_Node* begin() const;

    const XML_Node* end() const;
};





struct XML_Mapping {
    std::string content;
    std::unordered_map<std::string, XML_Mapping> map;

    XML_Mapping& operator[](const std::string& str);

    bool validity(const std::string& str);

    std::string get_string();

    int get_int();

    uint32_t get_uint32();

    float get_float();

    double get_double();

    bool get_bool();
};





class XML_Manager {
public:
    typedef XML_Node* iterator;
    typedef const XML_Node* const_iterator;

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

public:
    XML_Manager();

    std::string get_error();

    bool read(const std::string& path);

    void print();

    XML_Node* get(const std::string& title);

    void push_root_node(const XML_Node& node);

    void reset();

    bool save(const std::string& path);

    XML_Mapping get_map();

    void load_map(const XML_Mapping& map, int depth = 0);

private:
    void build_from_map(XML_Node& parent, const XML_Mapping& map);

    XML_Mapping build_map(const XML_Node& node);

    void write(const XML_Node& node, std::ofstream& stream, int depth);

    bool read_content(std::ofstream& file);

    std::pair<std::string, bool> read_balise(size_t& i, std::string& xml_str);

    void print_recursive(const XML_Node& node, int depth);

    std::vector<XML_Node> m_init_nodes;
    std::string m_error;
};