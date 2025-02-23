# SAPP: Semi-Probabilistic Adaptive Publish-Subscribe Protocol for MANETs

This repository contains an **OMNeT++** implementation of **SAPP**, a publish-subscribe protocol for **Mobile Ad Hoc Networks (MANETs)**. SAPP improves message delivery and subscription management in dynamic wireless environments by combining semi-probabilistic forwarding with adaptive retransmission intervals.

## Reference

This work is based on the research paper:

> **"Semi-Probabilistic Adaptive Publish-Subscribe Protocol for MANETs"**
> *Mohammed Almadhoun, Ahmed Qaddoura, Mohammad Owda, Aiman Ahmed Abusamra*
> *Published in I.J. Computer Network and Information Security, 2025, 6, 1-9*
> [DOI: TBD]

If you use this implementation, please cite the paper.

## Overview

Traditional IP-based routing in MANETs struggles with high mobility and frequent topology changes. Publish-subscribe (pub/sub) systems address this challenge by decoupling publishers and subscribers using topics, reducing the need for direct addressing.

SAPP improves on existing pub/sub solutions like **FADIP** by introducing:
- **Unicast forwarding** after discovering subscribers to reduce redundant broadcasts.
- **Adaptive retransmission intervals**, dynamically adjusting subscriber announcements based on mobility.
- **Acknowledgment-based subscription cleanup** to improve efficiency in high-mobility environments.

## Features

- Implements the **SAPP** protocol using **OMNeT++** for realistic MANET simulations.
- Supports **variable retransmission intervals** for subscriber announcements.
- Compares **SAPP vs. FADIP** in terms of **message delivery** and **network overhead**.
- Simulates various **mobility speeds** (0 mps, 2 mps, 10 mps) and **network sizes**.
- Includes **visualization scripts** for analyzing simulation results.

## Installation

### Prerequisites

1. **OMNeT++** (v6.0 or later) - [Installation Guide](https://omnetpp.org/documentation/)
2. **INET Framework** for wireless networking support - [INET Documentation](https://inet.omnetpp.org/)

### Setup Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/mohelm97/sapp-omnetpp.git
   cd sapp-omnetpp
   ```
2. Open the project in **OMNeT++ IDE**.
3. Ensure **INET** is properly configured.
4. Build the project.

## Usage

1. Open the `.ini` configuration files to define simulation parameters such as:
   - Number of nodes.
   - Mobility model (random walk, Gauss-Markov, etc.).
   - Simulation time.

2. Run the simulation from the OMNeT++ IDE.

3. Analyze the results using OMNeT++'s built-in tools for visualization and performance evaluation

## Evaluation Metrics

SAPP is evaluated based on:
- Broadcast overhead (total broadcast messages)
- Message delivery ratio (percentage of successfully received messages)
- Effectiveness of retransmission intervals (impact on performance)

## Project Structure

```
sapp-omnetpp/
 ├── src/            # SAPP protocol implementation
 ├── simulations/    # Configurations and scenarios
 ├── README.md       # This file
```

## Results

Our **OMNeT++ simulations** show that SAPP achieves:
- Lower broadcast overhead than FADIP.
- High message delivery rates even in high-mobility scenarios.
- Optimal performance with a **10s retransmission interval** for balancing overhead and delivery.

## Citation

If you use this repository in your research, please cite:

```bibtex
@article{almadhoun2025sapp,
  title={Semi-Probabilistic Adaptive Publish-Subscribe Protocol for MANETs},
  author={Almadhoun, Mohammed and Qaddoura, Ahmed and Owda, Mohammad and Abusamra, Aiman Ahmed},
  journal={I.J. Computer Network and Information Security},
  year={2025},
  volume={6},
  pages={1-9},
  publisher={MECS Press}
}
```

## Contributions

Contributions are welcome. Please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.  
