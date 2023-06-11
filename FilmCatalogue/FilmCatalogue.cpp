#include <iostream>
#include "Movie.h"
#include "MovieCatalog.h"
#include "Serializeable.h"
#include <fstream>


int main()
{
    Movie movie1("The Matrix", "Lana Wachowski", 1999, { 21, 30 }, 136);
    Movie movie2("Inception", "Christopher Nolan", 2010, { 19, 0 }, 148);
    Movie movie3("Interstellar", "Christopher Nolan", 2014, { 18, 45 }, 169);

    MovieCatalog catalog("Cinema");

    catalog.addMovie(movie1);
    catalog.addMovie(movie2);
    catalog.addMovie(movie3);

    std::ofstream outputFile("catalog.txt", std::ios::binary);
    catalog.serialize(outputFile);

    MovieCatalog* catalog2 = new MovieCatalog("catalog.txt");

   
    int moviesDuringThisTIme = catalog.getMoviesCountInTimeInterval({ 19, 0 }, { 22, 0 });
    std::cout << "Movies in range [19:00 - 22:00] ("<<moviesDuringThisTIme<<") :" << std::endl;

  
    return 0;
}

