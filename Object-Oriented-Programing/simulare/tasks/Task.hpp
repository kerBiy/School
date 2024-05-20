//
// Created by Alex Balta on 20.05.2024.
//

#pragma once

#include <string>
#include <utility>
#include <vector>

class Task {
  private:
    int id;
    std::string description;
    std::vector<std::string> programmers;
    std::string status;

  public:
    Task(int id, std::string description, std::vector<std::string> programmers, std::string status)
        : id(id), description(std::move(description)), programmers(std::move(programmers)), status(std::move(status)) {}

    int getId() const { return id; }
    std::string getDescription() const { return description; }
    std::vector<std::string> getProgrammers() const { return programmers; }
    std::string getStatus() const { return status; }

    void setStatus(const std::string &stat) { this->status = stat; }
};
