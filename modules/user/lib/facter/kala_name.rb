# kala_name.rb

Facter.add("kala_name") do
  setcode do
    Facter::Util::Resolution.exec('/bin/grep 1000 /etc/passwd | cut -f5 -d":" | tr -d \',\'')
  end
end

