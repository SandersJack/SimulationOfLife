DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIR=$(dirname "$(dirname "${DIR}")")

export SOLSOURCE="${DIR}/SimulationOfLife"
alias SOL="${SOLSOURCE}/build/SimulationOfLife"