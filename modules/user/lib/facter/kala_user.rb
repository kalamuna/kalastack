# kala_user.rb

Facter.add("kala_user") do
  setcode do
    Facter::Util::Resolution.exec('/usr/bin/getent passwd | grep 1000')
  end
end