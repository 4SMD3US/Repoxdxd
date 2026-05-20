// ===========================
//  Estado de la calculadora
// ===========================
let state = {
  expression: "",   // lo que se muestra arriba (historial)
  current: "0",     // número en pantalla
  operator: null,   // operador pendiente (+, -, *, /)
  prevValue: null,  // valor antes del operador
  justEvaluated: false  // flag: se acaba de pulsar "="
};

// ===========================
//  Referencias al DOM
// ===========================
const expressionEl = document.getElementById("expression");
const resultEl     = document.getElementById("result");

// ===========================
//  Actualizar pantalla
// ===========================
const updateDisplay = () => {
  resultEl.textContent     = state.current;
  expressionEl.textContent = state.expression || "";
};

// ===========================
//  Agregar dígito o punto
// ===========================
const appendDigit = (digit) => {
  if (state.justEvaluated) {
    state.current       = digit === "." ? "0." : digit;
    state.expression    = "";
    state.justEvaluated = false;
    updateDisplay();
    return;
  }

  if (digit === ".") {
    if (state.current.includes(".")) return;
    state.current += ".";
    updateDisplay();
    return;
  }

  state.current = state.current === "0" ? digit : state.current + digit;
  updateDisplay();
};

// ===========================
//  Seleccionar operador
// ===========================
const selectOperator = (op) => {
  const symbols = { "+": "+", "-": "−", "*": "×", "/": "÷" };

  if (state.operator && !state.justEvaluated) {
    calculate();   // encadena operaciones
  }

  state.prevValue      = parseFloat(state.current);
  state.operator       = op;
  state.expression     = `${state.current} ${symbols[op]}`;
  state.justEvaluated  = false;
  state.current        = "0";
  updateDisplay();
};

// ===========================
//  Calcular resultado
// ===========================
const calculate = () => {
  if (state.operator === null || state.prevValue === null) return;

  const prev    = state.prevValue;
  const current = parseFloat(state.current);
  const symbols = { "+": "+", "-": "−", "*": "×", "/": "÷" };

  const operations = {
    "+": (a, b) => a + b,
    "-": (a, b) => a - b,
    "*": (a, b) => a * b,
    "/": (a, b) => (b === 0 ? "Error" : a / b)
  };

  const result = operations[state.operator](prev, current);

  state.expression    = `${prev} ${symbols[state.operator]} ${current} =`;
  state.current       = result === "Error" ? "Error" : formatResult(result);
  state.operator      = null;
  state.prevValue     = null;
  state.justEvaluated = true;
  updateDisplay();
};

// ===========================
//  Formatear resultado
// ===========================
const formatResult = (num) => {
  if (Number.isInteger(num)) return String(num);
  const rounded = parseFloat(num.toFixed(10));
  return String(rounded);
};

// ===========================
//  Acciones especiales
// ===========================
const clear = () => {
  state = {
    expression: "",
    current: "0",
    operator: null,
    prevValue: null,
    justEvaluated: false
  };
  updateDisplay();
};

const toggleSign = () => {
  if (state.current === "0" || state.current === "Error") return;
  state.current = state.current.startsWith("-")
    ? state.current.slice(1)
    : "-" + state.current;
  updateDisplay();
};

const applyPercent = () => {
  if (state.current === "Error") return;
  state.current = String(parseFloat(state.current) / 100);
  updateDisplay();
};

// ===========================
//  Manejo de eventos
// ===========================
const handleButtonClick = (e) => {
  const btn = e.target.closest(".btn");
  if (!btn) return;

  const value  = btn.dataset.value;
  const action = btn.dataset.action;

  if (value !== undefined) {
    const operators = ["+", "-", "*", "/"];
    operators.includes(value) ? selectOperator(value) : appendDigit(value);
  }

  if (action) {
    const actions = {
      clear:   clear,
      sign:    toggleSign,
      percent: applyPercent,
      equals:  calculate
    };
    actions[action]?.();
  }
};

// Evento click en toda la grilla (delegación de eventos)
document.querySelector(".buttons-grid")
  .addEventListener("click", handleButtonClick);

// Soporte de teclado
const handleKeyDown = (e) => {
  const keyMap = {
    "0": () => appendDigit("0"),
    "1": () => appendDigit("1"),
    "2": () => appendDigit("2"),
    "3": () => appendDigit("3"),
    "4": () => appendDigit("4"),
    "5": () => appendDigit("5"),
    "6": () => appendDigit("6"),
    "7": () => appendDigit("7"),
    "8": () => appendDigit("8"),
    "9": () => appendDigit("9"),
    ".": () => appendDigit("."),
    "+": () => selectOperator("+"),
    "-": () => selectOperator("-"),
    "*": () => selectOperator("*"),
    "/": () => selectOperator("/"),
    "Enter":     calculate,
    "=":         calculate,
    "Backspace": () => {
      if (state.justEvaluated || state.current === "0") return;
      state.current = state.current.length > 1
        ? state.current.slice(0, -1)
        : "0";
      updateDisplay();
    },
    "Escape": clear
  };

  keyMap[e.key]?.();
};

document.addEventListener("keydown", handleKeyDown);

// ===========================
//  Inicialización
// ===========================
updateDisplay();
