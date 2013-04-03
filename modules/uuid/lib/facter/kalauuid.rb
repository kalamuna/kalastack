# kalauuid.rb

Facter.add("kalauuid") do
  setcode do
    Facter::Util::Resolution.exec("cat /etc/kalabox/uuid").chomp
  end
end