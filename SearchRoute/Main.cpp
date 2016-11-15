#include "route.h"
#include "lib_io.h"
#include "lib_time.h"
#include "stdio.h"


int main(int argc, char *argv[])
{
	print_time("Begin");
	char *topo[5000];
	int edge_num;
	char *demand;
	int demand_num;

	char *topo_file = argv[1];
	edge_num = read_file(topo, 5000, "topo.csv");
	if (edge_num == 0)
	{
		printf("Please input valid topo file.\n");
		return -1;
	}
	char *demand_file = argv[2];
	demand_num = read_file(&demand, 1, "demand.csv");
	if (demand_num != 1)
	{
		printf("Please input valid demand file.\n");
		return -1;
	}

	search_route(topo, edge_num, demand);

	char *result_file = argv[3];
	write_result("result.csv");
	release_buff(topo, edge_num);
	release_buff(&demand, 1);
	print_time("End");

// 	char* topo[5000] = { 
// 	"0,0,1,1",
// 	"1,0,2,2",
// 	"2,0,3,1",
// 	"4,3,1,1",
// 	"5,2,3,1",
// 	"6,3,2,1"};
// 	int edge_num = 6;
// 	char* demand = "0,1,2|3";
//	search_route(topo, edge_num, demand);
}