#include <iostream>

#include "Tools/data_file.hpp"
#include "mat/Math.hpp"

void display(const ora::DataNode& node, int depth = 0) {
    std::string depth_str;
    for (int i(0) ; i < depth ; ++i) {
        depth_str += "  ";
    }

    for (const auto& n : node.children) {

        std::cout << depth_str << n.first << " : " << n.second.content << std::endl;
        display(n.second, depth + 1);
    }
}

int main() {

    ora::DataNode node;

    node.children["engine"] = ora::DataNode();
    node.children["engine"].children["window"] = ora::DataNode();
    node.children["engine"].children["window"].children["width"] = ora::DataNode("1920");
    node.children["engine"].children["window"].children["height"] = ora::DataNode("1080");

    node.children["engine"].children["timer"] = ora::DataNode();
    node.children["engine"].children["timer"].children["fps"] = ora::DataNode("120");

    node["engine"]["Logger"]["LogFile"] = "output.log";
    node["texture"]["tree"]["path"] = "asset/img/tree.png";
    node["texture"]["tree"]["pixel"] = mat::Vector<float, 2>{300.0f, 200.0f};
    node["texture"]["tree"]["bpp"] = 3.0;
    mat::Matrix<int, 2, 3> mat{1,2,3,4,5,6};
    node["matrix"] = mat;
    std::cout << mat << std::endl;

    display(node);

    ora::DataFile data_file(node);

    data_file.save_txt("test/test.dat");

    data_file.load_txt("test/test.dat");

    ora::DataNode& root = data_file.get();

    display(root);

    mat::Vector<float, 2> texture_dimension = node["texture"]["tree"]["pixel"];
    mat::Matrix<int, 2, 3> mat_recover = node["matrix"];

    std::cout << "Texture dimension : " << texture_dimension << std::endl;
    std::cout << mat_recover << std::endl;

    return 0;
}