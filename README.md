# corewar

## Installation 

```bash
git clone [project]
make -C asm/
make -c vm/
```
## Usage
Create the .cor file
```bash
./asm/asm <file>
```
Run the virtual machine with the number of .cor file that you want.
Options: <br />
-a : Print the caracters from the aff command. <br />
-v : Visualizer
-dump: Jump to a certain number of cycle.
```bash
corewar [-a] [-v] [-dump <cycle>] [[-n <player number>] <executable> ...]
```

## Example
```bash
/vm/corewar vm_champs/champs/Gagnant.cor vm_champs/champs/Gagnant.cor
Introducing contestants..
Loading player 1: Celebration Funebre v0.99pl42 (Jour J)
Loading player 2: Celebration Funebre v0.99pl42 (Jour J)
Player 1, Celebration Funebre v0.99pl42 (Jour J), won!
```

## Authors
- Alexandre Le Goff
- Theo Kobb
- Anton Cakste
- Domitille Prevost

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

