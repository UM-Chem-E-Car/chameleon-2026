from pathlib import Path

root = Path('data')
tokens = [
    '------------------ Data Log:',
    'Waiting For Valve On',
    'VALVE IS ON',
    'Integration Time:',
    'FIRST DELTA HIT',
    'RXN DONE',
    'Calculated Distance:',
    'TIMETORUN:',
]

for path in sorted(root.glob('Run*.csv')):
    lines = path.read_text(encoding='utf-8', errors='ignore').splitlines()
    filtered = [line for line in lines if not any(token in line for token in tokens)]
    cleaned = '\n'.join(line for line in filtered if line.strip() != '') + '\n'
    path.write_text(cleaned, encoding='utf-8')
    print(path.name)
