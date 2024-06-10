import yfinance as yf
import sys

def fetch_data(ticker, start_date, end_date, filename):
	data = yf.download(ticker, start=start_date, end=end_date)
	data.to_csv(filename)
	print(f"Data successfully saved to {filename}.")

if __name__ == "__main__":
	if len(sys.argv) != 5:
		print("Usage: python3 fetch_data.py <ticker> <start_date> <end_date> <filename>")
		sys.exit(1)
	ticker = sys.argv[1]
	start_date = sys.argv[2]
	end_date = sys.argv[3]
	filename = sys.argv[4]
	fetch_data(ticker, start_date, end_date, filename)