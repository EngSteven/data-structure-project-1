# Priority Queue Management System

This repository contains the core implementation of a **priority-based queue management system** developed in C++ for the Data Structures course (IC-2001) at Instituto Tecnológico de Costa Rica.

## 📌 Project Overview

Waiting in line is a common experience in places like banks, hospitals, and government offices. This project simulates a **flexible, modular queue management system** that helps organize and prioritize customer service based on their user type and service request.

The system allows clients to request a ticket, be queued based on calculated priority, and be attended to at designated service windows. Priority is calculated using both the **user type** (e.g., elderly, disabled, regular user) and the **requested service** (e.g., buy a ticket, request information).

## 🔧 Features

- **Dynamic user interface via console menus** for interaction and simulation.
- **Custom user types** with configurable priority levels.
- **Service definition** linked to specific service areas and their own priority levels.
- **Configurable service areas** with named windows and priority queues.
- **Automatic ticket generation** with unique codes, timestamps, and computed priority.
- **Comprehensive administration tools**:
  - Add/remove user types, services, and areas.
  - Reorder services.
  - Reset statistics and queues.
- **Detailed system statistics**:
  - Average waiting time per area.
  - Number of tickets issued/attended per area, service, window, and user type.

## 🧮 Ticket Priority Formula

The priority of each ticket (PT) is calculated as:

PT = PU * 10 + PS


Where:
- `PU` is the priority of the user type.
- `PS` is the priority of the requested service.

A lower PT value means higher priority in the queue.

## 📋 Menu Structure

The application is organized into six main menu sections:

1. **Queue Status**
2. **Tickets**
   - Request a ticket
3. **Serve Clients**
   - Attend next ticket by window
4. **Administration**
   - User types, service areas, services, and system reset
5. **Statistics**
6. **Exit**

## 💡 Technologies

- **Language:** C++
- **Paradigm:** Object-Oriented Programming
- **Core Concepts:** Dynamic memory management, priority queues, structured menus

---
