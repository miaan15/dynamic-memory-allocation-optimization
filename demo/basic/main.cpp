#include <Eigen/Dense>
#include <iostream>
#include <toml++/toml.hpp>

auto main() -> int {
    Eigen::Matrix2d m;
    m << 1, 2, 3, 4;
    std::cout << "Eigen matrix:\n" << m << '\n';

    auto tbl = toml::parse(R"(
        [library]
        name = "toml++"
        authors = ["Mark Gillard <mark.gillard@outlook.com.au>"]
    )");

    std::cout << "\nTOML table:\n" << tbl << '\n';

    if (auto name = tbl["library"]["name"].value<std::string_view>()) {
        std::cout << "TOML library name: " << *name << '\n';
    } else {
        std::cout << "TOML library name not found\n";
    }

    return 0;
}

