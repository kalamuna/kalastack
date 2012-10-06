
class puppet::install {
	package { "puppet" : 
		ensure => present,
	}
}