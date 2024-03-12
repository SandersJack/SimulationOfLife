DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIR=$(dirname "$(dirname "${DIR}")")

export SOLSOURCE="${DIR}/SimulationOfLife"
export DOC_OUTPUT_DIR="${SOLSOURCE}/doc"

alias SOL="${SOLSOURCE}/build/SoL"