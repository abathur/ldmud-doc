switch {#driver_LPC_switch}
===========================
@usage{
switch(random(100)) {
  case 0 .. 22 : write("Nothing happens"); break;
  case 23 .. 27 :
    write("You are surrounded by a golden glow");
    this_player()->heal_self(random(3));
    break;
  case 28 .. 32 :
    write("The water was poisoned!\n");
    this_player()->add_exp(this_player()->hit_player(random(4)));
    break;
  case 33 : write("You hear a voice whispering: "+random_hint());
  /* fall through */
  case 34 :
    write(
      "While you didn't pay attention, a water demon "
      "snatches a coin out of your purse!\n"
    );
    this_player()->add_money(-1);
    break;
  default : write "You hear some strange noises\n"; break;
  case 42 : return;
  case 99 : write("It tastes good.\n";
}
}

See Also: 
   `for`, `foreach`, do-while(LPC), `if`, `while`
