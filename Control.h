#pragma once

using namespace std;

/**
 * Function declarations
 */
bool loadConfig(string fileName);

bool loadControlFeatures(string fileName);

int inConfig(vector<int> variables);

void printControlFeatures();