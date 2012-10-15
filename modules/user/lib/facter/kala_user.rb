# kala_user.rb

Facter.add("kala_user") do
  setcode do
    Facter::Util::Resolution.exec('/bin/uname -i')
  end
end