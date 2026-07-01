# Parsing Plan

Basically you need to take the arguments from the readline, which means :\
Read until we encounter a PIPE -> Store the value in a t_cmd struct as the ARGS value -> Set up the next Node with the pointer **next**\
		If it is a REDIR symbol, also store the TYPE and output file as the **t_redir** value INSIDE of the **t_cmd node**.

		Look in the header and inspect the structs beneath PARSING