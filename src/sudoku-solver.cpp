#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

namespace {

[[nodiscard]] auto parse_row(std::istream& file)
{
    if (!file)
        throw std::runtime_error("File is empty");

    auto line = std::string();
    std::getline(file, line);

    auto line_stream = std::istringstream(line);
    auto cell = std::string();
    auto result = std::array<int, 9>();
    for (size_t i = 0; std::getline(line_stream, cell, ','); ++i)
        result[i] = cell.empty() ? 0 : std::stoi(cell);

    return result;
}

[[nodiscard]] auto parse_csv(const std::string& filename)
{
    auto file = std::ifstream(filename);
    if (!file)
        throw std::runtime_error("File \"" + filename + "\" not found");

    auto grid = std::array<std::array<int, 9>, 9>();
    for (size_t row = 0; row < 9; ++row)
        grid[row] = parse_row(file);
    return grid;
}

[[nodiscard]] auto validate_set(const std::array<int, 9>& set)
{
    auto cell_counts = std::map<int, int>();
    for (const auto& cell : set)
        if (cell != 0)
            cell_counts[cell]++;
    for (const auto& cell_count : cell_counts)
        if (cell_count.second > 1)
            throw std::runtime_error("Cell " + std::to_string(cell_count.first) + " occurs "
                                     + std::to_string(cell_count.second) + " times");
}

[[nodiscard]] auto validate_grid(const std::array<std::array<int, 9>, 9>& grid)
{
    for (const auto& row : grid)
        validate_set(row);
}

[[nodiscard]] auto print_line(const std::array<int, 9>& line)
{
    const auto print_cell = [](const int cell) { return cell > 0 ? std::to_string(cell) : " "; };

    std::cout << "| " << print_cell(line[0]) << " | " << print_cell(line[1]) << " | " << print_cell(line[2]) << " |";
    std::cout << "| " << print_cell(line[3]) << " | " << print_cell(line[4]) << " | " << print_cell(line[5]) << " |";
    std::cout << "| " << print_cell(line[6]) << " | " << print_cell(line[7]) << " | " << print_cell(line[8]) << " |\n";
}

[[nodiscard]] auto print_divider(const size_t row)
{
    if (row % 3 > 0)
        std::cout << "---------------------------------------\n";
    else if (row < 9)
        std::cout << "=======================================\n";
}

[[nodiscard]] auto print_grid(const std::array<std::array<int, 9>, 9>& grid)
{
    for (size_t row = 0; row < 9; ++row) {
        print_line(grid[row]);
        print_divider(row + 1);
    }
}

}

int main()
try {
    const auto grid = parse_csv("grid.txt");
    validate_grid(grid);
    print_grid(grid);
} catch (const std::exception& exception) {
    std::cerr << exception.what() << std::endl;
    return EXIT_FAILURE;
}
