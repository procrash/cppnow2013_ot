I branched this off from Bryce Adelstein-Lelbach talk at CPPCon.

I wanted to have a condensed version which explains what is essential to Boost::Asio 
to serialize and deserialize classes and their derived children, automatically unpack them somewhere else (not necessary
transmitted via the network) and do function calls.

What the code is suffering now from is of course the zero copy approach from Bryce. 
