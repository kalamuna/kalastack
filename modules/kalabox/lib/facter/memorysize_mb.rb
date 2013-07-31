#
# Thanks Doug Warner
# https://groups.google.com/forum/#!topic/puppet-users/P91bvXV5iZI
#

require 'facter'

Facter.add("memorysize_mb") do
  confine :kernel => :Linux

  ram = 0

  # Steal linux's meminfo
  File.open( "/proc/meminfo" , 'r' ) do |f|
    f.grep( /^MemTotal:/ ) { |mem|
      ram = mem.split( / +/ )[1].to_i / 1024
    }
  end

  setcode do
    ram
  end
end
