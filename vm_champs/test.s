.name "zork"
.comment "I'M ALIIIIVE   "

live:
	add r1, r2, r3
	st r1, 255

loop:
  ld %42,r16
  and %:loop,%42,r4
  st r1, :live
