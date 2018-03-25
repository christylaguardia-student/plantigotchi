// forked & hacked from https://codepen.io/AriScott/pen/NGeRMR?editors=0010
import React from 'react';
import PropTypes from 'prop-types';

ImageSlider.propTypes = {
  hondas: PropTypes.arrayOf(PropTypes.object).isRequired,
  onUpdateSlide: PropTypes.func
};

Images.propTypes = {
  hondas: PropTypes.arrayOf(PropTypes.object).isRequired,
  active: PropTypes.number,
  onUpdateSlide: PropTypes.func

};

// Pagers.propTypes = {
//   hondas: PropTypes.arrayOf(PropTypes.object).isRequired,

// };

export default function ImageSlider({ hondas, onUpdateSlide }) {
  let active = 0;

  return (
    <div>
      <Images hondas={hondas} useImages={true} active={active} onClick={target => onUpdateSlide(target)}/>
    </div>
  );
}

export function Images({ hondas, active, onUpdateSlide }) {
  let width = { width: 100 / hondas.length + '%' };
  let divStyle = { left: active * -100 + '%', width: 4 * 100 + '%' };
  return (
    <div className="slider-wrapper">
      <ul className="slides" style={divStyle}>
        {hondas.map((honda, i) =>
          <li key={i} style={width}>
            <img src={honda.url} alt={honda.url}/>
          </li>
        )}
      </ul>
    </div>
  );
}

// export function Pagers({ hondas, onUpdateSlide }) {
//   let width = { width: 100 / hondas.length + '%' };
//   return (
//     <div>
//       <ul className="pagers">
//         {hondas.map((honda, i) =>
//           <li key={i} style={width}>{i} {honda}</li>
//         )}
//       </ul>
//     </div>
//   );
// }



      //     {/* <li key={i} style={width} onClick={target => updateSlide({ i })}/> */}

      // {/* React.createElement(Images, { items: this.props.slides, useImages: this.props.useImages, active: this.state.active }), */}
      // {/* React.createElement(Pagers, { items: this.props.slides, callbackParent: this.onPagerClicked }) */}

// React.render(
//   React.createElement(ImageSlider, {
//     useImages: 'false',
//     slides: ['image-1', 'image-2', 'image-3', 'image4']
//   }),
//   document.getElementById('react-container')
// );
