(
cd C:\...\download
g++ runthis.cpp -o runthis.exe
for /R C:\...\tests\ %G in (*) do runthis.exe %G false
)
