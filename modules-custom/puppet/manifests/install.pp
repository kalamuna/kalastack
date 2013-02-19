/**
 * 
 * Installs the puppet agent
 * 
 */
class puppet::install {
    
	package { "puppet" : 
		ensure => "2.7.11-1ubuntu2.1",
	}
	
}