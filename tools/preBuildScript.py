from Production.productCreationScript import main as product_main
from Production.productionChainCreationScript import main as chain_main
from Environment.mapCreationScript import main as map_main
from Environment.marketMapCreationScript import main as market_map_main
import time

sub_build_processes = [
    ("Product", product_main), 
    ("Production Chain", chain_main), 
    ("Map", map_main), 
    ("Market Map", market_map_main)
]

def main():
    dash_num = 60
    start_time = time.time()
    print("\nStarting pre-build process...")
    print("-" * dash_num + "\n")
    
    for name, func in sub_build_processes:
        print(f"\tBuilding {name} ...".ljust(dash_num - 23), end="")
        func()
        print(f"Finished")

    print("\n" + "-" * dash_num)
    print(f"Finished pre-build process in {time.time() - start_time:0.3f}s")




if __name__ == "__main__":
    main()
