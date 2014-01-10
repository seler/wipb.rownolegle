#!/usr/bin/env python
# -*- coding: utf-8 -*-

__author__ = u"Rafal Selewonko <rselewonko@murator.com.pl>"

import random


def rand_float(min, max):
    return (random.random() * (max - min)) + min


def new_specimen(s):
    return [rand_float(-1, 1) for x in range(s)]


def new_population(n, s):
    return [new_specimen(s) for x in range(n)]


def horner(x, polynomial):
    result = 0
    for coefficient in polynomial:
        result = result * x + coefficient
    return result


def specimen_fitness(specimen, x):
    return horner(x, specimen)


def population_fitness(population, x):
    return [specimen_fitness(specimen, x) for specimen in population]


def sorted_population(population, fitness):
    return [p for (f, p) in sorted(zip(fitness, population))]


def main():
    s = 4
    n = 10
    x = 2
    max_k = 2
    population = new_population(n, s)
    fitness = population_fitness(population, x)

    for k in range(max_k):
        tmp_population = new_population(n, s)
        tmp_fitness = population_fitness(population, x)
        #population = sorted_population(population + tmp_population, fitness + tmp_fitness)[:n]
        sorted_pop = [p for (f, p) in sorted(zip(fitness + tmp_fitness, population + tmp_population))]
        fitness = population_fitness(sorted_pop, x)
        print fitness

    #population = [p for (f, p) in sorted(zip(fitness, population))]
    print population_fitness(population, x)


if __name__ == '__main__':
    main()
