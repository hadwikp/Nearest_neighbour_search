# Nearest Neighbour Search

Efficient nearest-neighbour search over high-dimensional data, offering two approaches:

* **Brute-Force KNN**: Examines every data point to find the nearest neighbours.
* **Tree-Based KNN**: Utilizes KD-Tree and Random Projection Tree indexes for faster lookup.

## Features

* **DataVector ADT**: Dynamically resizable vectors with essential operations.
* **VectorDataset**: Manages collections of `DataVector` instances.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/nearest_neighbour_search.git
   cd nearest_neighbour_search
   ```
2. Unzip the dataset files into the project root.
3. Compile the code:

   ```bash
   # Brute-Force search executable
   g++ DataVector.cpp VectorDataset.cpp nearest_neighbour.cpp -o brute_force_demo

   # Tree-based search executable
   g++ DataVector.cpp VectorDataset.cpp TreeIndex.cpp nearest_neighbour1.cpp -o tree_search_demo
   ```

## Contributing

Contributions are welcome! Please open issues or pull requests for new features or fixes.
