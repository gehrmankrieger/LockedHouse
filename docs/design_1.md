# Locked House – One-Page Design

## Pitch
Locked House is a horror puzzle game where you escape a cult's house without getting caught by possessed bodies.

## Player actions
Walk, sprint, examine, pick up, aim, shoot, reload, heal (bandage), use item, save.
Bolt cutter halves auto-combine when the second half is picked up (no combine UI).

## Core loop
Explore room → find item/clue → open a lock → new room opens → repeat (threat interrupts)

## Setting and tone
Tense, dark, eerie mystery.

## Rooms
Map: `docs/map.png` (source: `docs/map.svg`). Numbered badges match the lock chain below.

![Floor plan](map.png)

| Room | What's here | Locked by |
| --- | --- | --- |
| Lobby (hub, stairs up) | Storage Key | Open (start) |
| Dining | Bolt cutter half A | Open |
| Storage | Gun, ammo, Kitchen Key, dial toolbox (contains Lockpick) | Storage Key |
| Kitchen (save room) | Ammo, bandage, Yard Key, cabinet (contains Master's Key), drawer (contains Bathroom Key) | Kitchen Key |
| Yard (small courtyard, via kitchen back door) | Bolt cutter half B | Yard Key |
| Upstairs hallway | Doors to Master's, Bath, Attic; one sealed door (never opens) | Open |
| Master's | Dial code clue (317), ammo | Master's Key |
| Bath | Bandage, ammo, attic clue | Bathroom Key |
| Attic | Ending | 4-digit keypad |

Attic clue: count the knives (Kitchen), frames (Lobby), spoons (Dining), shoes (Master's) → 4-digit code.

## Lock chain (critical path)
1. Lobby: Storage Key
2. Storage: Gun, ammo, Kitchen Key (toolbox is locked)
3. Dining: Bolt cutter half A
4. Kitchen: Yard Key (cabinet and drawer are locked)
5. Yard: Bolt cutter half B → auto-combine → Bolt Cutter
6. Kitchen cabinet (Bolt Cutter): Master's Key
7. Master's: dial code clue
8. Storage toolbox (code 317): Lockpick
9. Kitchen drawer (Lockpick): Bathroom Key
10. Bath: attic clue
11. Attic keypad (4-digit code): ending

## Puzzles
| Puzzle | Player must figure out | Answer | Tag on solve |
| --- | --- | --- | --- |
| Kitchen cabinet | The chain needs a bolt cutter, in two halves | Combine halves, use on cabinet | `World.Puzzle.Cabinet.Solved` |
| Toolbox dial | Read the clue in Master's | 317 | `World.Puzzle.Dial.Solved` |
| Attic keypad | Count objects in 4 rooms, in clue order | TBD (each digit 1–9) | `World.Puzzle.Pin.Solved` |

## Enemies
- **Melee:** slow movement, slow attacks.
- **Melee+:** faster movement and attacks, more HP, one heavy attack on a cooldown.
- Same enemy class, two stat sets.
- Rule: no enemies before the player has the gun (Storage).

## Items and inventory
- Keys are stored as Gameplay Tags (e.g. `Item.Key.Storage`) and shown as a simple list.
- Ammo and bandages are HUD counters.
- Bandages: 4 total. Ammo: 30–40 rounds. Enemies: 5–7 total.

Combat numbers (draft, tune during playtest):
- Melee: 5 HP. Melee+: 10 HP.
- Shots: 2 damage to the head, 1 to the body.

## Save room
Kitchen. Save at the memo pad on the fridge.

## Win / lose
- Win: correct code at attic keypad → end screen (play again / quit).
- Lose: HP reaches 0 → reload last save / quit.

## Cut list
Map screen, knife, item box, multiple endings, boss, multiplayer, grab, grid inventory, combine UI, stalker.

## Open questions
- What form the dial clue takes in Master's (e.g. three stopped clocks).
- Attic code counts (pick the four digits).
- Exact Melee+ heavy attack damage; ammo/bandage tuning (playtest).
- Can enemies enter the kitchen save room?
- Where enemies are placed (first encounter after Storage; lobby threat after a story beat?).
- Stretch: randomized codes per playthrough, stalker enemy, grab attack.
