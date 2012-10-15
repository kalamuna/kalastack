# kala_user.rb

Facter.add("kala_user") do
  setcode do
    Facter::Util::Resolution.exec("usr/bin/getent passwd | awk -F: '$3 == 1000 { print $1 }'")
  end
end
