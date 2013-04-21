ipcs = `ipcs | grep -i '^m\s' | awk {'print $2'}`.split("\n")
ipcs.each { |ipc| system "ipcrm -m #{ipc}" }