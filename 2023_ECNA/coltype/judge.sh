
solution=$1
test_data_dir=$2

for i in $test_data_dir/*.in; do
		correct="${i/in/ans}"
		./$solution < $i > output
		echo "[*] $i"
		diff -w output $correct
		rm output
done


