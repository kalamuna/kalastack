# To use, put following in ~/.bashrc:
# Include my custom dot files
if [ -f ~/.mallis_money ]; then
  . ~/.mallis_money
fi

# We set this environmental variable so 
# it is ingested into $_SERVER by php
# This basically exists only so drush
# kaladata runs. We are also setting it
# through nginx. @todo is this dumb?  
export KALABOX = on

# Inspirations:
# https://github.com/paulirish/dotfiles